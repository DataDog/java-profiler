---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-09 03:28:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 262 |
| Sample Rate | 4.37/sec |
| Health Score | 273% |
| Threads | 15 |
| Allocations | 153 |

<details>
<summary>CPU Timeline (2 unique values: 28-36 cores)</summary>

```
1791530596 28
1791530601 28
1791530606 28
1791530611 36
1791530616 36
1791530621 36
1791530626 36
1791530631 36
1791530636 36
1791530641 36
1791530646 36
1791530651 36
1791530656 36
1791530661 36
1791530666 36
1791530671 36
1791530676 36
1791530681 36
1791530686 36
1791530691 36
```
</details>

---

