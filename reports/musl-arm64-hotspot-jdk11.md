---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-02 12:03:19 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 11 |
| Allocations | 172 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 26-31 cores)</summary>

```
1790956723 26
1790956728 26
1790956733 26
1790956738 26
1790956743 26
1790956748 26
1790956753 26
1790956758 26
1790956763 26
1790956768 26
1790956773 26
1790956778 26
1790956783 26
1790956789 26
1790956794 26
1790956799 26
1790956804 26
1790956809 26
1790956814 26
1790956819 31
```
</details>

---

