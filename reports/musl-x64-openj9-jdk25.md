---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 17:33:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 10 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 90-96 cores)</summary>

```
1789680172 96
1789680177 96
1789680182 96
1789680187 96
1789680192 96
1789680197 96
1789680202 96
1789680207 96
1789680212 96
1789680217 96
1789680222 96
1789680227 96
1789680232 96
1789680237 96
1789680242 96
1789680247 96
1789680252 96
1789680257 90
1789680262 90
1789680267 90
```
</details>

---

