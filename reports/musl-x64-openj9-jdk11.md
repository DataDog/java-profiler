---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 10:20:21 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 850 |
| Sample Rate | 14.17/sec |
| Health Score | 886% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (4 unique values: 60-76 cores)</summary>

```
1790259137 60
1790259142 60
1790259147 60
1790259152 60
1790259157 62
1790259162 62
1790259167 64
1790259172 64
1790259177 64
1790259182 76
1790259187 76
1790259192 76
1790259197 76
1790259202 76
1790259207 76
1790259212 76
1790259217 76
1790259222 76
1790259227 76
1790259232 76
```
</details>

---

