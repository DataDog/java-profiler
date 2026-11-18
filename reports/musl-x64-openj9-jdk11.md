---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 13:43:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (4 unique values: 46-52 cores)</summary>

```
1795027128 48
1795027133 48
1795027138 48
1795027143 48
1795027148 48
1795027153 48
1795027158 48
1795027163 48
1795027168 48
1795027173 50
1795027178 50
1795027183 50
1795027188 50
1795027193 50
1795027198 50
1795027203 50
1795027208 50
1795027213 52
1795027218 52
1795027223 52
```
</details>

---

