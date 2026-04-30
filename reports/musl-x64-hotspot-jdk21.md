---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-30 10:30:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1004 |
| Sample Rate | 16.73/sec |
| Health Score | 1046% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 59-71 cores)</summary>

```
1777559056 71
1777559061 71
1777559066 71
1777559072 71
1777559077 71
1777559082 71
1777559087 71
1777559092 71
1777559097 63
1777559102 63
1777559107 63
1777559112 63
1777559117 59
1777559122 59
1777559127 59
1777559132 59
1777559137 59
1777559142 59
1777559147 59
1777559152 63
```
</details>

---

