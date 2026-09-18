---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:49:03 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 70-76 cores)</summary>

```
1789731841 72
1789731846 72
1789731851 72
1789731856 72
1789731861 70
1789731866 70
1789731871 70
1789731876 72
1789731881 72
1789731886 72
1789731891 72
1789731896 72
1789731901 72
1789731906 72
1789731911 74
1789731916 74
1789731921 76
1789731926 76
1789731931 76
1789731936 76
```
</details>

---

