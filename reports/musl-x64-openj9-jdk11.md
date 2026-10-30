---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 08:18:32 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 427 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 9 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (3 unique values: 70-76 cores)</summary>

```
1793362353 70
1793362358 70
1793362363 70
1793362368 70
1793362373 70
1793362378 70
1793362383 70
1793362388 70
1793362393 70
1793362398 70
1793362403 70
1793362408 74
1793362413 74
1793362418 76
1793362423 76
1793362428 76
1793362433 76
1793362438 76
1793362443 76
1793362448 76
```
</details>

---

