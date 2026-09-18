---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 02:30:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 8 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 946 |
| Sample Rate | 15.77/sec |
| Health Score | 986% |
| Threads | 8 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 17-24 cores)</summary>

```
1789712758 17
1789712763 17
1789712768 17
1789712773 17
1789712778 17
1789712783 17
1789712788 17
1789712793 17
1789712798 17
1789712803 17
1789712808 17
1789712813 17
1789712818 17
1789712823 24
1789712828 24
1789712833 24
1789712838 24
1789712843 24
1789712848 24
1789712853 24
```
</details>

---

