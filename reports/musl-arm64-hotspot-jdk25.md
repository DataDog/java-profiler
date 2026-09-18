---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 09:25:38 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 13 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 8 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1789737704 44
1789737709 44
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
1789737779 48
1789737784 48
1789737789 48
1789737794 48
1789737799 48
```
</details>

---

