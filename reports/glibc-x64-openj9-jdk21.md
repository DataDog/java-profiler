---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 03:32:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 324 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 424 |

<details>
<summary>CPU Timeline (3 unique values: 76-96 cores)</summary>

```
1789716430 94
1789716435 94
1789716440 94
1789716445 96
1789716450 96
1789716455 96
1789716460 96
1789716465 96
1789716470 96
1789716475 96
1789716480 96
1789716485 76
1789716490 76
1789716495 76
1789716501 76
1789716506 76
1789716511 76
1789716516 76
1789716521 76
1789716526 76
```
</details>

---

