---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 17:26:11 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 80-81 cores)</summary>

```
1789680090 80
1789680095 80
1789680100 80
1789680105 80
1789680110 80
1789680115 80
1789680120 81
1789680125 81
1789680130 81
1789680135 81
1789680140 81
1789680145 81
1789680150 81
1789680155 81
1789680160 81
1789680165 81
1789680170 81
1789680175 81
1789680180 81
1789680185 81
```
</details>

---

