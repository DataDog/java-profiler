---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-23 05:22:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 217 |
| Sample Rate | 3.62/sec |
| Health Score | 226% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 38-55 cores)</summary>

```
1795429067 55
1795429072 55
1795429077 55
1795429082 55
1795429087 55
1795429092 55
1795429097 38
1795429102 38
1795429107 38
1795429112 38
1795429117 38
1795429122 38
1795429127 38
1795429132 38
1795429137 38
1795429142 38
1795429147 38
1795429152 38
1795429157 38
1795429162 38
```
</details>

---

