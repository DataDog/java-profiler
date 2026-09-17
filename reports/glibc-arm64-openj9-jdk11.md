---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 15:42:09 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 11 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1789673521 40
1789673526 40
1789673531 40
1789673536 40
1789673541 40
1789673546 40
1789673551 40
1789673556 40
1789673561 40
1789673566 40
1789673571 40
1789673576 40
1789673581 40
1789673586 40
1789673591 40
1789673596 40
1789673601 40
1789673606 40
1789673611 40
1789673616 40
```
</details>

---

