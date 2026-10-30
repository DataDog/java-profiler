---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 09:38:18 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 830 |
| Sample Rate | 13.83/sec |
| Health Score | 864% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (3 unique values: 49-73 cores)</summary>

```
1793367192 52
1793367197 52
1793367202 52
1793367207 52
1793367212 52
1793367217 52
1793367222 52
1793367227 52
1793367232 52
1793367237 52
1793367242 52
1793367247 52
1793367252 52
1793367257 73
1793367262 73
1793367267 73
1793367272 73
1793367277 49
1793367282 49
1793367287 49
```
</details>

---

