---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-02 12:03:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (3 unique values: 31-37 cores)</summary>

```
1790956719 37
1790956724 37
1790956729 37
1790956734 37
1790956739 37
1790956744 37
1790956749 31
1790956754 31
1790956759 31
1790956764 31
1790956769 31
1790956774 31
1790956779 31
1790956784 31
1790956789 31
1790956794 31
1790956799 31
1790956804 31
1790956809 31
1790956815 31
```
</details>

---

