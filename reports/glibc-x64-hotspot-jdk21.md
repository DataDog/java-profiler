---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:30:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 12 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 65-96 cores)</summary>

```
1795631086 65
1795631091 65
1795631096 65
1795631101 65
1795631106 93
1795631111 93
1795631116 93
1795631121 93
1795631126 93
1795631131 93
1795631136 93
1795631141 93
1795631146 93
1795631151 93
1795631156 93
1795631161 93
1795631166 96
1795631171 96
1795631176 96
1795631181 96
```
</details>

---

