---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 16:48:48 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 321 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1789677727 32
1789677732 32
1789677737 32
1789677742 32
1789677747 32
1789677752 32
1789677757 32
1789677762 32
1789677767 32
1789677772 32
1789677777 32
1789677782 32
1789677787 32
1789677792 32
1789677797 32
1789677802 32
1789677807 32
1789677812 30
1789677817 30
1789677822 30
```
</details>

---

