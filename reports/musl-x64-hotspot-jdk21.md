---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-31 00:55:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 826 |
| Sample Rate | 13.77/sec |
| Health Score | 861% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (5 unique values: 66-76 cores)</summary>

```
1788151853 74
1788151858 74
1788151863 74
1788151868 76
1788151873 76
1788151878 76
1788151883 76
1788151888 76
1788151893 76
1788151898 76
1788151903 76
1788151908 76
1788151913 76
1788151918 76
1788151923 76
1788151928 76
1788151933 66
1788151938 66
1788151943 66
1788151948 66
```
</details>

---

