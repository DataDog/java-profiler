---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:30:43 EST

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 552 |

<details>
<summary>CPU Timeline (3 unique values: 70-96 cores)</summary>

```
1795631074 93
1795631079 93
1795631084 93
1795631089 96
1795631094 96
1795631099 96
1795631104 96
1795631109 96
1795631114 96
1795631119 96
1795631124 96
1795631129 96
1795631134 96
1795631139 96
1795631144 96
1795631149 70
1795631154 70
1795631159 70
1795631164 70
1795631169 70
```
</details>

---

