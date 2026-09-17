---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 16:47:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 95 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 869 |
| Sample Rate | 14.48/sec |
| Health Score | 905% |
| Threads | 11 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (3 unique values: 94-96 cores)</summary>

```
1789677737 94
1789677742 94
1789677747 94
1789677752 94
1789677757 94
1789677762 94
1789677767 94
1789677772 94
1789677777 94
1789677782 94
1789677787 94
1789677792 96
1789677797 96
1789677802 96
1789677807 96
1789677812 96
1789677817 96
1789677822 95
1789677827 95
1789677832 95
```
</details>

---

