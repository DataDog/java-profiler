---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-08 10:54:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 50-54 cores)</summary>

```
1791470928 54
1791470933 54
1791470938 54
1791470943 54
1791470948 54
1791470953 54
1791470958 54
1791470963 54
1791470968 52
1791470973 52
1791470978 52
1791470983 50
1791470988 50
1791470993 50
1791470998 50
1791471003 50
1791471008 50
1791471013 50
1791471018 50
1791471023 50
```
</details>

---

