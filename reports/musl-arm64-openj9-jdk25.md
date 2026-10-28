---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 09:32:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 13 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1793194101 36
1793194106 36
1793194112 36
1793194117 36
1793194122 36
1793194127 36
1793194132 36
1793194137 36
1793194142 36
1793194147 36
1793194152 36
1793194157 36
1793194162 36
1793194167 36
1793194172 36
1793194177 36
1793194182 36
1793194187 36
1793194192 36
1793194197 36
```
</details>

---

