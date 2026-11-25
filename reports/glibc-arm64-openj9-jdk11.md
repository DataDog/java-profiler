---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:30:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 361 |
| Sample Rate | 6.02/sec |
| Health Score | 376% |
| Threads | 11 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 26-30 cores)</summary>

```
1795631117 30
1795631122 30
1795631127 30
1795631132 30
1795631137 30
1795631142 30
1795631147 30
1795631152 30
1795631157 26
1795631162 26
1795631167 26
1795631172 26
1795631177 26
1795631182 26
1795631187 26
1795631192 26
1795631197 26
1795631202 26
1795631207 26
1795631212 26
```
</details>

---

