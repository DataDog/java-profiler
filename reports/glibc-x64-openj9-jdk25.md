---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-29 11:09:01 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 68-77 cores)</summary>

```
1777475049 77
1777475054 77
1777475059 77
1777475064 77
1777475069 77
1777475074 77
1777475079 77
1777475084 77
1777475089 77
1777475094 77
1777475099 77
1777475104 77
1777475109 77
1777475114 77
1777475119 77
1777475124 77
1777475129 77
1777475134 73
1777475139 73
1777475144 68
```
</details>

---

