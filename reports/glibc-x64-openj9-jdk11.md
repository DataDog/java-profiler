---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 10:20:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (5 unique values: 52-96 cores)</summary>

```
1790259107 54
1790259112 54
1790259117 52
1790259122 52
1790259127 84
1790259132 84
1790259137 84
1790259142 84
1790259147 86
1790259152 86
1790259157 86
1790259162 96
1790259167 96
1790259172 96
1790259177 96
1790259182 96
1790259187 96
1790259192 96
1790259197 96
1790259202 96
```
</details>

---

