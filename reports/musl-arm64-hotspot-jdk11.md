---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 08:43:16 EST

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 7 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (3 unique values: 13-64 cores)</summary>

```
1795786659 13
1795786664 13
1795786669 13
1795786674 13
1795786679 13
1795786684 13
1795786689 13
1795786694 13
1795786699 13
1795786704 13
1795786709 13
1795786714 13
1795786719 33
1795786724 33
1795786729 33
1795786734 33
1795786739 33
1795786744 33
1795786749 33
1795786754 33
```
</details>

---

