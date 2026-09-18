---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:07:46 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 61-96 cores)</summary>

```
1789743555 61
1789743560 61
1789743565 61
1789743570 61
1789743575 61
1789743580 61
1789743585 94
1789743590 94
1789743595 94
1789743600 94
1789743605 94
1789743610 94
1789743615 94
1789743620 94
1789743625 94
1789743630 96
1789743635 96
1789743640 96
1789743645 96
1789743650 96
```
</details>

---

