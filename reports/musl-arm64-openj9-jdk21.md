---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-14 08:33:45 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1791980917 48
1791980922 48
1791980927 48
1791980932 48
1791980937 48
1791980942 48
1791980947 48
1791980952 48
1791980957 48
1791980962 48
1791980967 48
1791980972 48
1791980977 48
1791980982 48
1791980987 48
1791980992 48
1791980997 48
1791981002 48
1791981007 48
1791981012 48
```
</details>

---

