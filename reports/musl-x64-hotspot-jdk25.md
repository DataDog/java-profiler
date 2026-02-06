---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-06 10:50:48 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 11 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 833 |
| Sample Rate | 13.88/sec |
| Health Score | 868% |
| Threads | 12 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 86-96 cores)</summary>

```
1770392712 96
1770392717 96
1770392722 96
1770392727 96
1770392732 96
1770392737 96
1770392742 96
1770392747 96
1770392752 96
1770392757 96
1770392762 96
1770392767 96
1770392772 96
1770392777 96
1770392782 96
1770392787 96
1770392792 96
1770392797 96
1770392802 96
1770392807 91
```
</details>

---

