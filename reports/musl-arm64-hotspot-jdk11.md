---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 05:45:41 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 13 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (4 unique values: 46-64 cores)</summary>

```
1794480067 51
1794480072 51
1794480077 51
1794480082 51
1794480087 51
1794480092 51
1794480097 51
1794480102 46
1794480107 46
1794480112 46
1794480117 46
1794480122 46
1794480127 46
1794480132 46
1794480137 46
1794480142 46
1794480147 46
1794480152 46
1794480157 59
1794480162 59
```
</details>

---

