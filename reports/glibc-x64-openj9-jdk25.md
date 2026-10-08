---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-08 12:33:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 10 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (2 unique values: 46-63 cores)</summary>

```
1791476949 63
1791476954 63
1791476959 63
1791476964 63
1791476969 63
1791476974 63
1791476979 63
1791476984 63
1791476989 63
1791476994 63
1791476999 63
1791477004 63
1791477009 63
1791477014 63
1791477019 46
1791477024 46
1791477029 46
1791477034 46
1791477039 46
1791477044 46
```
</details>

---

