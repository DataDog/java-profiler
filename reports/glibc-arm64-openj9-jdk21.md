---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 11:01:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794326132 51
1794326137 51
1794326142 51
1794326147 51
1794326152 51
1794326157 51
1794326162 51
1794326167 51
1794326172 51
1794326177 46
1794326182 46
1794326187 46
1794326192 46
1794326197 46
1794326202 46
1794326207 46
1794326212 46
1794326217 46
1794326222 46
1794326227 46
```
</details>

---

