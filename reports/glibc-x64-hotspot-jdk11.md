---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 08:26:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 10 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (4 unique values: 88-96 cores)</summary>

```
1795785689 88
1795785694 88
1795785699 88
1795785704 88
1795785709 88
1795785714 88
1795785719 88
1795785724 88
1795785729 88
1795785734 88
1795785739 96
1795785744 96
1795785749 96
1795785754 96
1795785759 96
1795785764 96
1795785769 96
1795785774 96
1795785779 96
1795785784 94
```
</details>

---

