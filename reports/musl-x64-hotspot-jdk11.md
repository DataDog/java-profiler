---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 17:14:15 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 989 |
| Sample Rate | 16.48/sec |
| Health Score | 1030% |
| Threads | 11 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (2 unique values: 83-85 cores)</summary>

```
1795471734 83
1795471739 83
1795471744 83
1795471749 85
1795471754 85
1795471759 85
1795471764 85
1795471769 85
1795471775 85
1795471780 85
1795471785 85
1795471790 85
1795471795 85
1795471800 85
1795471805 85
1795471810 85
1795471815 85
1795471820 85
1795471825 85
1795471830 85
```
</details>

---

