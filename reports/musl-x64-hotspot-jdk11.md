---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-05 05:23:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1001 |
| Sample Rate | 16.68/sec |
| Health Score | 1042% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 39-42 cores)</summary>

```
1770286708 42
1770286713 42
1770286718 42
1770286723 42
1770286728 42
1770286733 42
1770286738 42
1770286743 42
1770286748 39
1770286753 39
1770286758 39
1770286763 39
1770286768 39
1770286773 39
1770286778 39
1770286783 39
1770286788 39
1770286793 39
1770286798 39
1770286803 39
```
</details>

---

