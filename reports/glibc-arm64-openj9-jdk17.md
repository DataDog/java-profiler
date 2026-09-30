---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-30 12:30:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 10 |
| Allocations | 114 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1790785507 46
1790785512 46
1790785517 46
1790785522 46
1790785527 46
1790785532 46
1790785537 46
1790785542 46
1790785547 46
1790785552 46
1790785557 46
1790785562 46
1790785567 46
1790785572 46
1790785577 46
1790785582 46
1790785587 46
1790785592 46
1790785597 46
1790785602 46
```
</details>

---

