---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 09:47:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 42-50 cores)</summary>

```
1794408132 47
1794408137 42
1794408142 42
1794408147 42
1794408152 50
1794408157 50
1794408162 50
1794408167 50
1794408172 50
1794408177 50
1794408182 50
1794408187 50
1794408192 50
1794408197 50
1794408202 50
1794408207 50
1794408212 50
1794408217 50
1794408222 50
1794408227 50
```
</details>

---

