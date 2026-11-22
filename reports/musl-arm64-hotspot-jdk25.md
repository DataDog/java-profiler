---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-22 15:41:02 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 84 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795379764 34
1795379769 34
1795379774 34
1795379779 34
1795379784 34
1795379789 34
1795379794 34
1795379799 34
1795379804 34
1795379809 34
1795379814 34
1795379819 34
1795379824 34
1795379829 34
1795379834 34
1795379839 34
1795379844 34
1795379849 29
1795379854 29
1795379859 29
```
</details>

---

