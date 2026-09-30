---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 07:31:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1790767647 40
1790767652 40
1790767657 40
1790767662 40
1790767667 40
1790767672 40
1790767677 40
1790767682 40
1790767687 40
1790767692 40
1790767697 40
1790767702 40
1790767707 40
1790767712 40
1790767717 40
1790767722 40
1790767727 40
1790767732 40
1790767737 40
1790767742 40
```
</details>

---

