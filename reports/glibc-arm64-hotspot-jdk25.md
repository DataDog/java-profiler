---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 07:20:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 248 |
| Sample Rate | 4.13/sec |
| Health Score | 258% |
| Threads | 11 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795436165 64
1795436170 64
1795436175 64
1795436180 64
1795436185 64
1795436190 64
1795436195 64
1795436200 64
1795436205 64
1795436210 64
1795436215 64
1795436220 64
1795436225 64
1795436230 64
1795436235 64
1795436240 64
1795436245 64
1795436250 64
1795436255 64
1795436260 64
```
</details>

---

