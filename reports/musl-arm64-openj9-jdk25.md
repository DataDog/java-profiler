---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 07:23:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 266 |
| Sample Rate | 4.43/sec |
| Health Score | 277% |
| Threads | 11 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 45-53 cores)</summary>

```
1790853549 53
1790853554 53
1790853559 53
1790853564 53
1790853569 53
1790853574 53
1790853579 53
1790853584 53
1790853589 53
1790853595 53
1790853600 45
1790853605 45
1790853610 45
1790853615 45
1790853620 45
1790853625 45
1790853630 45
1790853635 45
1790853640 45
1790853645 45
```
</details>

---

