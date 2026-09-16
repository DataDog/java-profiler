---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-16 12:11:38 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 234 |
| Sample Rate | 3.90/sec |
| Health Score | 244% |
| Threads | 9 |
| Allocations | 146 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 13 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1789574804 46
1789574809 46
1789574814 46
1789574819 46
1789574824 46
1789574829 46
1789574834 48
1789574839 48
1789574844 48
1789574849 48
1789574854 48
1789574859 48
1789574864 48
1789574869 48
1789574874 48
1789574879 48
1789574884 48
1789574889 48
1789574894 48
1789574899 48
```
</details>

---

