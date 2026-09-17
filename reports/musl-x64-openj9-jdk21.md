---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 16:50:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 95 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 90-95 cores)</summary>

```
1789677752 95
1789677757 95
1789677762 95
1789677767 95
1789677772 95
1789677777 95
1789677782 95
1789677787 95
1789677792 95
1789677797 95
1789677802 95
1789677807 93
1789677812 93
1789677817 93
1789677822 93
1789677827 93
1789677832 93
1789677837 93
1789677842 93
1789677847 93
```
</details>

---

