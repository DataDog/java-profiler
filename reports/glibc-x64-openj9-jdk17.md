---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-06 15:13:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 10 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (2 unique values: 13-34 cores)</summary>

```
1793995721 34
1793995726 34
1793995731 34
1793995736 34
1793995741 34
1793995746 34
1793995751 34
1793995756 34
1793995761 34
1793995766 34
1793995771 13
1793995776 13
1793995781 13
1793995786 13
1793995791 13
1793995796 13
1793995802 13
1793995807 13
1793995812 13
1793995817 13
```
</details>

---

