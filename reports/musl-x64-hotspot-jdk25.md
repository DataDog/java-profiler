---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:44:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (4 unique values: 24-96 cores)</summary>

```
1789731592 24
1789731597 24
1789731602 55
1789731607 55
1789731612 55
1789731617 55
1789731622 55
1789731627 55
1789731632 55
1789731637 55
1789731642 55
1789731647 55
1789731652 55
1789731657 55
1789731662 55
1789731667 75
1789731672 75
1789731677 96
1789731682 96
1789731687 96
```
</details>

---

