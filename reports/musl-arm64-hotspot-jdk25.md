---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-16 12:13:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 37-48 cores)</summary>

```
1789574772 48
1789574777 48
1789574782 48
1789574787 48
1789574792 48
1789574797 48
1789574802 48
1789574807 48
1789574812 48
1789574817 48
1789574822 48
1789574827 48
1789574832 48
1789574837 48
1789574842 48
1789574847 48
1789574852 44
1789574857 44
1789574862 37
1789574867 37
```
</details>

---

