---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 07:20:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 11 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (6 unique values: 39-48 cores)</summary>

```
1795436140 41
1795436145 41
1795436150 41
1795436155 39
1795436160 39
1795436165 39
1795436170 44
1795436175 44
1795436180 44
1795436185 44
1795436190 44
1795436195 44
1795436200 44
1795436205 44
1795436210 44
1795436215 44
1795436220 46
1795436225 46
1795436230 46
1795436235 48
```
</details>

---

