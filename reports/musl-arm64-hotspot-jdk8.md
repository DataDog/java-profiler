---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-18 09:29:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1789737714 44
1789737719 44
1789737724 44
1789737729 44
1789737734 44
1789737739 44
1789737744 44
1789737749 44
1789737754 44
1789737759 44
1789737764 44
1789737769 44
1789737774 44
1789737779 44
1789737784 44
1789737789 64
1789737794 64
1789737799 64
1789737804 64
1789737809 64
```
</details>

---

