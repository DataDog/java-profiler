---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 10:44:07 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 877 |
| Sample Rate | 14.62/sec |
| Health Score | 914% |
| Threads | 9 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 85-91 cores)</summary>

```
1790779112 91
1790779117 91
1790779122 91
1790779127 87
1790779132 87
1790779137 87
1790779142 87
1790779147 85
1790779152 85
1790779157 85
1790779162 87
1790779167 87
1790779172 87
1790779177 87
1790779182 89
1790779187 89
1790779192 89
1790779197 91
1790779202 91
1790779207 91
```
</details>

---

