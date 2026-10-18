---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-18 05:54:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 901 |
| Sample Rate | 15.02/sec |
| Health Score | 939% |
| Threads | 8 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792316935 46
1792316940 46
1792316945 46
1792316950 46
1792316955 46
1792316960 46
1792316965 46
1792316970 46
1792316975 46
1792316980 46
1792316985 46
1792316990 46
1792316995 46
1792317000 51
1792317005 51
1792317010 51
1792317015 51
1792317020 51
1792317025 51
1792317030 51
```
</details>

---

