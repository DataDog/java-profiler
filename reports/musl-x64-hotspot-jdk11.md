---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:41:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 899 |
| Sample Rate | 14.98/sec |
| Health Score | 936% |
| Threads | 9 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1789716637 94
1789716642 94
1789716647 94
1789716652 94
1789716657 94
1789716662 94
1789716667 94
1789716672 94
1789716677 94
1789716682 94
1789716687 94
1789716692 94
1789716697 94
1789716702 96
1789716707 96
1789716712 96
1789716717 96
1789716722 96
1789716727 96
1789716732 96
```
</details>

---

