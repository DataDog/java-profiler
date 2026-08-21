---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-21 10:44:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 7 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (4 unique values: 30-34 cores)</summary>

```
1787323165 30
1787323170 30
1787323175 31
1787323180 31
1787323185 32
1787323190 32
1787323195 32
1787323200 32
1787323205 32
1787323210 32
1787323215 32
1787323220 34
1787323225 34
1787323230 34
1787323235 34
1787323240 34
1787323245 34
1787323250 34
1787323255 34
1787323260 34
```
</details>

---

