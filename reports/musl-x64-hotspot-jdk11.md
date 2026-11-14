---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-14 16:39:50 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 10 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (3 unique values: 71-81 cores)</summary>

```
1794692101 71
1794692106 71
1794692111 79
1794692116 79
1794692121 79
1794692126 79
1794692131 79
1794692136 79
1794692141 79
1794692146 79
1794692151 79
1794692156 79
1794692161 81
1794692166 81
1794692171 81
1794692176 81
1794692181 81
1794692186 81
1794692191 81
1794692196 81
```
</details>

---

