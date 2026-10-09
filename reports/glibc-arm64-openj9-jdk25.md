---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-09 07:11:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 159 |
| Sample Rate | 2.65/sec |
| Health Score | 166% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 343 |
| Sample Rate | 5.72/sec |
| Health Score | 358% |
| Threads | 16 |
| Allocations | 178 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1791544074 51
1791544079 51
1791544084 51
1791544089 51
1791544094 51
1791544099 51
1791544104 51
1791544109 51
1791544114 51
1791544119 51
1791544124 51
1791544129 51
1791544134 51
1791544139 51
1791544144 51
1791544149 51
1791544154 51
1791544159 51
1791544164 46
1791544169 46
```
</details>

---

