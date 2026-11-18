---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:33:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 12 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 11 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 33-46 cores)</summary>

```
1795015634 33
1795015639 33
1795015644 33
1795015649 33
1795015654 33
1795015659 33
1795015664 33
1795015669 33
1795015674 33
1795015679 33
1795015684 33
1795015689 33
1795015694 33
1795015699 33
1795015704 33
1795015709 33
1795015714 33
1795015719 46
1795015724 46
1795015729 46
```
</details>

---

