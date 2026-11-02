---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-01 20:28:12 EST

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 9 |
| Allocations | 131 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 11 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1793582673 16
1793582678 16
1793582683 16
1793582688 16
1793582693 16
1793582698 16
1793582703 16
1793582708 16
1793582713 16
1793582718 16
1793582723 16
1793582728 16
1793582733 16
1793582738 16
1793582743 16
1793582748 16
1793582753 16
1793582758 16
1793582763 16
1793582768 16
```
</details>

---

