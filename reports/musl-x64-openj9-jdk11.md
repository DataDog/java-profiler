---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 11:30:20 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 749 |
| Sample Rate | 12.48/sec |
| Health Score | 780% |
| Threads | 8 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 22-32 cores)</summary>

```
1790090656 22
1790090661 22
1790090666 22
1790090671 22
1790090676 22
1790090681 22
1790090686 22
1790090691 22
1790090696 22
1790090701 22
1790090706 22
1790090711 22
1790090716 22
1790090721 22
1790090727 22
1790090732 22
1790090737 22
1790090742 22
1790090747 22
1790090752 22
```
</details>

---

