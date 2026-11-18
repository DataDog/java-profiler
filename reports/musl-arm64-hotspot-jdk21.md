---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 13:43:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 7 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 28-64 cores)</summary>

```
1795027108 28
1795027113 28
1795027118 28
1795027123 28
1795027128 28
1795027133 28
1795027138 28
1795027143 28
1795027148 28
1795027153 28
1795027158 28
1795027163 28
1795027168 28
1795027173 28
1795027178 28
1795027183 28
1795027188 64
1795027193 64
1795027198 51
1795027203 51
```
</details>

---

